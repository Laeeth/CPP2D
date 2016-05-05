#pragma warning(push, 0)
#pragma warning(disable, 4702)
#include <llvm/Support/Path.h>
#include <clang/AST/ASTContext.h>
#pragma warning(pop)

using namespace llvm;
using namespace clang;


namespace CPP2DTools
{

const char* getFile(clang::SourceManager const& sourceManager, clang::SourceLocation const& sl)
{
	if(sl.isValid() == false)
		return "";
	clang::FullSourceLoc fsl = FullSourceLoc(sl, sourceManager).getExpansionLoc();
	auto& mgr = fsl.getManager();
	if(clang::FileEntry const* f = mgr.getFileEntryForID(fsl.getFileID()))
		return f->getName();
	else
		return nullptr;
}


const char* getFile(clang::SourceManager const& sourceManager, Stmt const* d)
{
	return getFile(sourceManager, d->getLocStart());
}

const char* getFile(clang::SourceManager const& sourceManager, Decl const* d)
{
	return getFile(sourceManager, d->getLocation());
}

bool checkFilename(std::string const& modulename, char const* filepath_str)
{
	if(filepath_str == nullptr)
		return false;
	std::string filepath = filepath_str;
	if(filepath.size() < 12)
		return false;
	else
	{
		StringRef const filename = llvm::sys::path::filename(filepath);
		static char const* exts[] = { ".h", ".hpp", ".cpp", ".cxx", ".c" };
		auto iter = std::find_if(std::begin(exts), std::end(exts), [&](auto && ext)
		{
			return filename == (modulename + ext);
		});
		return iter != std::end(exts);
	}
}

bool checkFilename(clang::SourceManager const& sourceManager,
                   std::string const& modulename,
                   clang::Decl const* d)
{
	return checkFilename(modulename, getFile(sourceManager, d));
}

} //CPP2DTools